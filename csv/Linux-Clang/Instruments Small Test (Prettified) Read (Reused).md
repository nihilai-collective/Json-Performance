
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3783.53 | 0.0776461 | 207.314ms | 7932 | 30 | 72.2989 | 1999.33 | 0.233957 | 0.645945 | 1(Win) | true |
| Jsonifier | 2334.95 | 0.0835825 | 352.754ms | 7932 | 40 | 293.292 | 3239.7 | 0.0359986 | 1.05177 | 2(Loss) | true |
| Glaze | 2174.84 | 0.0366337 | 348.687ms | 7932 | 160 | 259.771 | 3478.2 | 0.0761308 | 1.1295 | 3(Loss) | true |
| simdjson (ondemand) | 1008.93 | 0.0630816 | 743.588ms | 7932 | 30 | 671.076 | 7497.6 | 0.0760822 | 2.44537 | 4(Loss) | true |
