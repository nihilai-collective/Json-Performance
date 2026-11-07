
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1915.43 | 0.147892 | 4768.33ms | 83958 | 1280 | 4.89208e+06 | 41802 | 0.237356 | 1.29161 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1891.64 | 0.0470894 | 4871.81ms | 83958 | 40 | 15891 | 42327.5 | 0.0295229 | 1.30787 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1888.32 | 0.0988621 | 4795.37ms | 83958 | 2560 | 4.49857e+06 | 42402.1 | 0.0679413 | 1.31033 | 2(Tie) | true |
| simdjson (ondemand) | 1332.1 | 0.27946 | 6582.89ms | 83958 | 160 | 4.51448e+06 | 60106.9 | 0.109061 | 1.8576 | 4(Loss) | true |
