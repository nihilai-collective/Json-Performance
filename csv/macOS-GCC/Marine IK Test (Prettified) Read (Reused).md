
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1907.62 | 1.02128 | 6156.42ms | 7351818 | 30 | 4.22683e+10 | 3.67539e+06 | 2.68662 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 1904.34 | 1.79095 | 5714.06ms | 7351818 | 30 | 1.30434e+11 | 3.68172e+06 | 5.406 | -(Tie) | false |
| simdjson (reflection) | 1744.22 | 0.336125 | 6568.3ms | 7351818 | 80 | 1.46042e+10 | 4.0197e+06 | 0.430016 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 1530.18 | 0.785401 | 7816.74ms | 7351818 | 30 | 3.88516e+10 | 4.58197e+06 | 0.298495 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1504.66 | 0.76562 | 7630.98ms | 7351818 | 80 | 1.01819e+11 | 4.65968e+06 | 0.399558 | 4(Tie) | true |
