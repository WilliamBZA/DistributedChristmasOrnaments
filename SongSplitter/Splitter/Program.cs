// Splitter for songs from: https://github.com/robsoncouto/arduino-songs

var skip = 0;
var take = 999;


var originalTempo = 114;
var className = "NeverGonnaGiveYouUp";
var raw = @"NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, 
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, 
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2";

var tempoMultiplier = 160.0 / originalTempo;

if (raw.Contains("//"))
{
    throw new Exception("Input string contains comments");
}

var items = raw.Split(",", StringSplitOptions.RemoveEmptyEntries);

var notes = items.Select((x, i) => i % 2 == 0 ? x.Trim().Replace("\r\n", string.Empty) : null).Where(i => i != null).Skip(skip).Take(take).ToList();
var tempo = items.Select((x, i) => i % 2 == 0 ? null : Math.Round(Convert.ToInt32(x.Trim().Replace("\r\n", string.Empty)) / tempoMultiplier, MidpointRounding.AwayFromZero).ToString()).Where(i => i != null).Skip(skip).Take(take).ToList();



Console.WriteLine(@$"class {className} : public Song {{
  public:
    {className}(int buzzPin);
}};");

Console.WriteLine();
Console.WriteLine();

Console.WriteLine($@"{className}::{className}(int buzzPin) : Song(buzzPin, new int [{notes.Count + 1}] {{ {notes.Count + 1},
  {string.Join(", ", notes)}
}}, new int [{notes.Count}] {{ {string.Join(", ", tempo)} }}) {{
}};");

Console.WriteLine();
Console.WriteLine();

Console.WriteLine($"else if (songName == \"{className.ToLower()}\") {{ return {className}(BUZZER_PIN); }}");



Console.WriteLine();
Console.WriteLine();

Console.WriteLine($"<li><a href=\"/api/play?song={className}\">{className}</a></li>");