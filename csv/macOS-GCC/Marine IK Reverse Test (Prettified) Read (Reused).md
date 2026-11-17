
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2058.91 | 0.233193 | 5682.66ms | 7351818 | 80 | 5.0447e+09 | 3.40531e+06 | 2.04569 | 1(Win) | true |
| Jsonifier (two-stage) | 2003.12 | 0.220847 | 5809.86ms | 7351818 | 80 | 4.78023e+09 | 3.50017e+06 | 0.331499 | 2(Loss) | true |
| simdjson (reflection) | 1843.55 | 0.257923 | 6369.79ms | 7351818 | 80 | 7.6975e+09 | 3.80311e+06 | 0.498573 | 3(Loss) | true |
| Glaze | 1581.49 | 0.624991 | 7387.29ms | 7351818 | 30 | 2.30316e+10 | 4.43331e+06 | 1.52326 | 4(Loss) | true |
| simdjson (ondemand) | 1556.86 | 0.398026 | 7066.16ms | 7351818 | 30 | 9.63908e+09 | 4.50346e+06 | 1.65773 | 5(Loss) | true |
