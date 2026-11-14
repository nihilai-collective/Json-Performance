
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1957.29 | 0.0551566 | 9040.82ms | 183677 | 2560 | 6.23785e+06 | 89495.3 | 0.117076 | 1(Win) | true |
| simdjson (ondemand) | 1725.71 | 0.139757 | 5383.58ms | 183677 | 320 | 6.43978e+06 | 101505 | 0.0291697 | 2(Loss) | true |
