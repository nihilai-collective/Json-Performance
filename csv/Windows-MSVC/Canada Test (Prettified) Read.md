
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 21800.3 | 0.521137 | 6017.99ms | 5373214 | 30 | 4.50163e+07 | 235057 | 0.0411418 | 0.113551 | 1(Win) | true |
| simdjson (stage-1) | 17438.5 | 0.516079 | 7528.16ms | 5373214 | 30 | 6.89929e+07 | 293850 | 0.633475 | 0.141954 | 2(Loss) | true |
