
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 921.659 | 0.655761 | 8169.02ms | 5212421 | 80 | 1.00074e+11 | 5.39348e+06 | 1.35454 | 3.29759 | 1(Win) | true |
| simdjson (ondemand) | 823.223 | 1.04066 | 9025.46ms | 5212421 | 30 | 1.18464e+11 | 6.0384e+06 | 0.688106 | 3.68919 | 2(Loss) | true |
