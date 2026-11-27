
----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4761.91 | 0.770803 | 6353.88ms | 10018896 | 30 | 7.17603e+09 | 2.0065e+06 | 0.291036 | 0.51991 | 1(Win) | true |
| Glaze | 2695.4 | 0.187084 | 5393.4ms | 9930228 | 30 | 1.29619e+09 | 3.51347e+06 | 0.487833 | 0.918524 | 2(Loss) | true |
