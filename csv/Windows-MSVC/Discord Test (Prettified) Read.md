
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1203.49 | 0.0503126 | 6657.5ms | 83958 | 4890 | 5.47898e+06 | 66530.1 | 0.0797467 | 2.52444 | 1(Win) | true |
| simdjson (ondemand) | 1140.89 | 0.0408587 | 7029.93ms | 83958 | 4890 | 4.02083e+06 | 70180.8 | 0.0749709 | 2.66307 | 2(Loss) | true |
