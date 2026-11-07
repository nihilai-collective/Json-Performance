
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1231.06 | 0.21626 | 6714.01ms | 2251027 | 30 | 4.26654e+08 | 1.74381e+06 | 0.718159 | 2.01107 | 1(Win) | true |
| Jsonifier (two-stage) | 1128.81 | 0.0403309 | 7179.87ms | 2251027 | 160 | 9.41268e+07 | 1.90177e+06 | 0.182163 | 2.19324 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 911.803 | 0.313296 | 8701.59ms | 2251027 | 160 | 8.7054e+09 | 2.3544e+06 | 0.153503 | 2.71525 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 907.731 | 0.0458403 | 8753.6ms | 2251027 | 80 | 9.40226e+07 | 2.36496e+06 | 0.268009 | 2.72742 | 3(Tie) | true |
