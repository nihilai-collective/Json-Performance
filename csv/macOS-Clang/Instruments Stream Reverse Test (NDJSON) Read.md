
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 777.088 | 0.0996831 | 7881.39ms | 4197496 | 40 | 1.05473e+09 | 5.15134e+06 | 2.91163 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 531.156 | 0.0441676 | 5415.43ms | 4197496 | 40 | 4.43205e+08 | 7.53647e+06 | 11.7266 | -(Loss) | false |
