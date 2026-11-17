
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 197.905 | 0.532477 | 7215.6ms | 2090234 | 40 | 1.15064e+11 | 1.00725e+07 | 0.987598 | 12.5102 | 1(Win) | true |
| simdjson (ondemand) | 190.108 | 0.584616 | 7354.45ms | 2090234 | 40 | 1.5031e+11 | 1.04856e+07 | 0.624971 | 13.0231 | 2(Loss) | true |
