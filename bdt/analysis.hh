// Header file of the analysis code
double GetZa(double s, double b, double db)
{
  double t1=(s+b)*TMath::Log((s+b)*(b+db*db)/(b*b+(s+b)*db*db));
  double t2=b*b/(db*db)*TMath::Log(1+db*db*s/(b*(b+db*db)));
  double result=TMath::Sqrt(2*(t1-t2));
  if(result != result || std::isinf(result)) result = 0;
  return result;
}

double GetZ(double s, double b)
{
  float su, bu,z,zu;
  su=TMath::Sqrt(s);
  bu=TMath::Sqrt(b);
  z=s/TMath::Sqrt(b);
  zu=z*TMath::Sqrt((su*su)/(s*s)+(bu*bu)/(b*b));

  std::cout<<"\tuncertainty is: "<<zu<<std::endl;
  return s/TMath::Sqrt(b);
}
