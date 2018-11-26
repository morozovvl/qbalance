if (tovarName.toUpperCase().indexOf("АВТОВАЗ") > -1 || tovarName.toUpperCase().indexOf("KRAFT") > -1)
{
  tovarPrice = tovarPrice * ((100-6.2) / 100);
}
else if (tovarName.toUpperCase().indexOf("FENOX") > -1)
{
  tovarPrice = tovarPrice * ((100-7.2) / 100);
}


