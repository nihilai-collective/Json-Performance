
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21498.8 | 0.248271 | 812.616ms | 183677 | 640 | 261887 | 8147.8 | 0.106103 | 0.114661 | 1(Win) | true |
| simdjson (stage-1) | 19589.3 | 0.0364116 | 904.272ms | 183677 | 30 | 318.033 | 8942.03 | 0.0484838 | 0.125991 | 2(Loss) | true |
