
----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16004.4 | 0.148033 | 4296.84ms | 716365 | 640 | 2.55556e+06 | 42687 | 0.0363635 | 0.154596 | 1(Win) | true |
| Glaze | 4733.63 | 0.047953 | 7373.22ms | 716365 | 2560 | 1.22617e+07 | 144325 | 0.0577271 | 0.522864 | 2(Loss) | true |
