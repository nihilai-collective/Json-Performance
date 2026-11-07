
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1844.53 | 0.0882053 | 3434.01ms | 56369 | 4890 | 3.23153e+06 | 29144.4 | 0.0223926 | 1.34105 | 1(Win) | true |
| Glaze | 1484.93 | 0.0966814 | 4174.77ms | 56369 | 2560 | 3.13613e+06 | 36202.1 | 0.334128 | 1.6661 | 2(Loss) | true |
| Jsonifier (two-stage) | 1329.17 | 0.105041 | 4609.93ms | 56369 | 2560 | 4.62038e+06 | 40444.6 | 0.00791916 | 1.86136 | 3(Loss) | true |
| simdjson (ondemand) | 941.079 | 0.287138 | 6268.84ms | 56369 | 320 | 8.60914e+06 | 57123.4 | 0.0300793 | 2.62953 | 4(Loss) | true |
