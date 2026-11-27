
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 483.822 | 0.414182 | 7775.98ms | 5212421 | 40 | 7.24351e+10 | 1.02743e+07 | 0.211189 | 5.11723 | 1(Win) | true |
| simdjson (ondemand) | 471.093 | 1.16296 | 7801.37ms | 5212421 | 30 | 4.51772e+11 | 1.05519e+07 | 0.650243 | 5.25551 | 2(Loss) | true |
