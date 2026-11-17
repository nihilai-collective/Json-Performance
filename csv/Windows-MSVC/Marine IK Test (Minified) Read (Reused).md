
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 680.845 | 0.336228 | 8808.17ms | 1834197 | 160 | 1.19394e+10 | 2.5692e+06 | 0.512155 | 4.4637 | 1(Win) | true |
| Jsonifier (two-stage) | 610.267 | 0.325154 | 9709.68ms | 1834197 | 160 | 1.3898e+10 | 2.86633e+06 | 0.170565 | 4.97987 | 2(Loss) | true |
| simdjson (ondemand) | 323.19 | 0.260981 | 8533.71ms | 1834197 | 40 | 7.98094e+09 | 5.41238e+06 | 0.0422618 | 9.40412 | 3(Loss) | true |
| Glaze | 314.497 | 0.30655 | 8776.3ms | 1834197 | 40 | 1.16284e+10 | 5.56198e+06 | 0.101808 | 9.66425 | 4(Loss) | true |
