
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 951.139 | 0.427831 | 7827.03ms | 5212421 | 80 | 3.99969e+10 | 5.22631e+06 | 0.0781514 | 3.19533 | 1(Win) | true |
| simdjson (ondemand) | 927.872 | 0.364945 | 8047.25ms | 5212421 | 80 | 3.05807e+10 | 5.35737e+06 | 0.357568 | 3.27509 | 2(Loss) | true |
