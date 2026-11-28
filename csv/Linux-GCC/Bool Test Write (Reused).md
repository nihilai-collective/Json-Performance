
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3125.88 | 0.142554 | 35.7277ms | 905 | 160 | 24.7874 | 276.106 | 0.0158428 | 0.713619 | 1(Win) | true |
| simdjson (reflection) | 2389.47 | 0.232355 | 42.9176ms | 905 | 30 | 21.131 | 361.2 | 0.0921999 | 0.959374 | 2(Loss) | true |
| Glaze | 1062.2 | 0.0925828 | 89.8299ms | 905 | 320 | 181.09 | 812.534 | 0.137881 | 2.25027 | 3(Loss) | true |
