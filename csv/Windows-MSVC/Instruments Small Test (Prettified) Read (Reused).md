
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1636.7 | 0.0788219 | 485.046ms | 7932 | 4890 | 64898.2 | 4621.84 | 0.166875 | 1.84917 | 1(Win) | true |
| simdjson (ondemand) | 1511.35 | 0.0708263 | 530.061ms | 7932 | 4890 | 61452.1 | 5005.17 | 0.603944 | 2.00278 | 2(Loss) | true |
