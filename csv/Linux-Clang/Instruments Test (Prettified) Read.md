
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2735.33 | 0.243829 | 6464.69ms | 183677 | 80 | 1.95053e+06 | 64039.2 | 0.144495 | 0.904731 | 1(Win) | true |
| simdjson (ondemand) | 2534 | 0.0827966 | 6998.67ms | 183677 | 640 | 2.09654e+06 | 69127.1 | 0.0149227 | 0.976671 | 2(Loss) | true |
