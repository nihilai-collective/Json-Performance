
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 896.994 | 0.346641 | 6079.7ms | 56369 | 320 | 1.38106e+07 | 59930.9 | 0.595559 | 2.75878 | 1(Win) | true |
| simdjson (ondemand) | 775.979 | 0.115403 | 7017.05ms | 56369 | 2560 | 1.63627e+07 | 69277.2 | 0.0990843 | 3.18926 | 2(Loss) | true |
