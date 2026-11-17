
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2400.4 | 0.0326382 | 1740ms | 25388 | 2560 | 27744.7 | 10086.6 | 0.0108076 | 2.13837 | 9.30692 | 1.69281 | 0.00320693 | 1.17858e-05 | 3.49267e-06 | 1(Win) | true |
| simdjson (ondemand) | 2137.46 | 0.0459556 | 1875ms | 25388 | 640 | 17342.8 | 11327.4 | 0.0641146 | 2.41743 | 10.3023 | 1.71481 | 0.00314531 | 2.99723e-05 | 1.76634e-05 | 2(Loss) | true |
