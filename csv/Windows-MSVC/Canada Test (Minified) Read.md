
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 24171.9 | 0.342787 | 8908.52ms | 2251027 | 320 | 2.96577e+07 | 88811.6 | 0.039777 | 0.102391 | 1(Win) | true |
| simdjson (stage-1) | 17615.6 | 0.116048 | 6231.45ms | 2251027 | 2560 | 5.12015e+07 | 121866 | 0.28794 | 0.14051 | 2(Loss) | true |
