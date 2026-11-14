
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 470.918 | 1.07229 | 8185.48ms | 5212421 | 40 | 5.12475e+11 | 1.05559e+07 | 0.510335 | 5.25732 | 1(Win) | true |
| simdjson (ondemand) | 436.05 | 1.20606 | 8525.86ms | 5212421 | 30 | 5.67111e+11 | 1.14e+07 | 0.114022 | 5.67764 | 2(Loss) | true |
