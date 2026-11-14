
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2868.11 | 0.187963 | 271.175ms | 7932 | 30 | 737.292 | 2637.47 | 0.0531094 | 1(Win) | true |
| Jsonifier (two-stage) | 2581.13 | 0.0367588 | 300.453ms | 7932 | 640 | 742.761 | 2930.72 | 0.0134335 | 2(Loss) | true |
| Glaze | 1751.24 | 0.186814 | 440.145ms | 7932 | 30 | 1953.5 | 4319.53 | 0.0300868 | 3(Loss) | true |
| simdjson (ondemand) | 1019.29 | 0.0492632 | 753.609ms | 7932 | 160 | 2138.63 | 7421.39 | 0.0134728 | 4(Loss) | true |
