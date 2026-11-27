
----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.371 | 0.0186209 | 8316.54ms | 56369 | 4890 | 962857 | 75357.2 | 0.20538 | 7.14292 | 33.6446 | 7.18865 | 0.0102447 | 5.80639e-05 | 4.07409e-05 | 1(Win) | true |
| simdjson (ondemand) | 200.213 | 0.0411817 | 7038.9ms | 56369 | 1280 | 1.56501e+07 | 268503 | 0.0335396 | 25.3696 | 139.875 | 28.1045 | 0.0394688 | 0.000111015 | 7.57703e-05 | 2(Loss) | true |
