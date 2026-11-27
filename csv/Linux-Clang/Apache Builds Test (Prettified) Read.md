
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16307.2 | 0.0434968 | 1450.67ms | 124597 | 2560 | 25716.3 | 7286.65 | 0.0202466 | 0.316758 | 1.74552 | 0.103695 | 1.64813e-05 | 2.72754e-06 | 1.62399e-06 | 1(Win) | true |
| simdjson (stage-1) | 14632 | 0.0231619 | 1526.82ms | 124597 | 4890 | 17300.7 | 8120.89 | 0.142137 | 0.350916 | 1.64961 | 0.0692794 | 1.63308e-05 | 3.0413e-06 | 1.61502e-06 | 2(Loss) | true |
