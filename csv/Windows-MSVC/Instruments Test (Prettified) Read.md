
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1575.25 | 0.19 | 5745.77ms | 183677 | 1280 | 5.71385e+07 | 111200 | 0.49912 | 1.57129 | 1(Win) | true |
| simdjson (ondemand) | 1284.21 | 0.331196 | 7038.12ms | 183677 | 320 | 6.53065e+07 | 136401 | 0.11055 | 1.92746 | 2(Loss) | true |
