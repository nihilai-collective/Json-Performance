
----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12712 | 0.147512 | 37.9226ms | 4669 | 160 | 42.7164 | 350.275 | 0.0749973 | 0.180701 | 1(Win) | true |
| simdjson (reflection) | 8679.21 | 0.0917357 | 54.0454ms | 4669 | 160 | 35.4393 | 513.031 | 0.144762 | 0.270366 | 2(Loss) | true |
| Glaze | 2051.21 | 0.126856 | 221.231ms | 4669 | 80 | 606.658 | 2170.78 | 0.265328 | 1.19202 | 3(Loss) | true |
