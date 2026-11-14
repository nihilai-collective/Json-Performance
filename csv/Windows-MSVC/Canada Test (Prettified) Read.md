
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26158.5 | 0.112295 | 5108.13ms | 5373214 | 640 | 3.09701e+07 | 195894 | 0.133026 | 0.0946319 | 1(Win) | true |
| simdjson (stage-1) | 19805.4 | 1.33981 | 6921.54ms | 5373214 | 40 | 4.80674e+08 | 258732 | 0.408337 | 0.124986 | 2(Loss) | true |
