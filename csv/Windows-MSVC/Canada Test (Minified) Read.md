
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27639.6 | 0.259499 | 7789.81ms | 2251027 | 320 | 1.29993e+07 | 77669.4 | 0.178154 | 0.0895356 | 1(Win) | true |
| simdjson (stage-1) | 19349.4 | 0.707995 | 5675.1ms | 2251027 | 30 | 1.85102e+07 | 110947 | 0.045087 | 0.127906 | 2(Loss) | true |
