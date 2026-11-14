
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2632.08 | 0.0931233 | 6791.01ms | 183677 | 640 | 2.45816e+06 | 66551.3 | 0.0515987 | 0.940227 | 1(Win) | true |
| simdjson (ondemand) | 2444.16 | 0.19365 | 7360.53ms | 183677 | 320 | 6.16365e+06 | 71668.1 | 0.289175 | 1.01257 | 2(Loss) | true |
