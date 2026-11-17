
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2861.6 | 0.0801075 | 6336.65ms | 183677 | 4890 | 1.17584e+07 | 61213.4 | 0.0232161 | 0.864769 | 1(Win) | true |
| simdjson (ondemand) | 2573.17 | 0.092641 | 6999.35ms | 183677 | 4890 | 1.94486e+07 | 68074.8 | 0.136469 | 0.961769 | 2(Loss) | true |
