
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 442.842 | 1.36305 | 8042.14ms | 5212421 | 30 | 7.02303e+11 | 1.12251e+07 | 0.198209 | 5.59063 | 1(Win) | true |
| simdjson (ondemand) | 412.956 | 1.36836 | 8536.88ms | 5212421 | 30 | 8.13941e+11 | 1.20375e+07 | 0.336776 | 5.99521 | 2(Loss) | true |
