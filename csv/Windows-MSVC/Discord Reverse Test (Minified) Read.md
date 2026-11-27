
----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 496.382 | 0.133656 | 5538.11ms | 56369 | 2560 | 5.36374e+07 | 108299 | 0.125895 | 6.12155 | 1(Win) | true |
| simdjson (ondemand) | 168.889 | 0.115028 | 8122.18ms | 56369 | 160 | 2.14487e+07 | 318302 | 0.195774 | 17.995 | 2(Loss) | true |
