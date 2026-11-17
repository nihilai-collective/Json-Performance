
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 483.9 | 0.462647 | 7322.63ms | 5212421 | 40 | 9.03498e+10 | 1.02727e+07 | 0.714005 | 5.11635 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 456.588 | 0.496822 | 7723.13ms | 5212421 | 40 | 1.17029e+11 | 1.08872e+07 | 6.32876 | 5.42245 | -(Loss) | false |
