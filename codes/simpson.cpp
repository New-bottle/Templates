double getf(double x) {
}
double calc(double l, double fl, double fimd, double fr) {
	return (fl + fmid * 4 + fr) * 1 / 6;
}
double simpson(double l, double mid, double r, double fl, double fmid, double fr, double s) {
	double m1 = (l + mid) / 2, m2 = (mid + r) / 2;
	double f1 = getf(m1), f2 = getf(m2);
	double g1 = calc(mid - l, fl, f1, fmid), g2 = calc(r - mid, fmid, f2, fr);
	if (fabs(g1 + g2 - s) < eps) return g1 + g2;
	return simpson(l, m1, mid, fl, f1, mid, g1) +
		   simpson(mid, m2, r, fmid, f2, fr, g2);
}
