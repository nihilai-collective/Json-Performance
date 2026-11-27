
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 29591.5 | 0.0566553 | 7282.99ms | 2251027 | 4890 | 8.26072e+06 | 72546.1 | 0.0488908 | 0.0836347 | 1(Win) | true |
| simdjson (stage-1) | 20244.9 | 0.0712021 | 5437.48ms | 2251027 | 2560 | 1.45933e+07 | 106039 | 0.164556 | 0.122258 | 2(Loss) | true |
