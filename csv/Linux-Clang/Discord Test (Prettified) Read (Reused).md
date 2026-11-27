
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2477.63 | 0.103006 | 4306.04ms | 83958 | 1280 | 1.41835e+06 | 32316.5 | 0.0257687 | 2.04892 | 9.33405 | 1.66038 | 0.00327647 | 1.11384e-05 | 6.5602e-06 | 1(Win) | true |
| simdjson (ondemand) | 2024.72 | 0.0416206 | 5083.8ms | 83958 | 4890 | 1.32471e+06 | 39545.5 | 0.357716 | 2.50833 | 10.2852 | 1.59539 | 0.00896325 | 1.56764e-05 | 9.4896e-06 | 2(Loss) | true |
