
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1493.54 | 0.182077 | 6706.87ms | 94653 | 40 | 484405 | 60439.1 | 0.0905725 | 3.43606 | 15.0311 | 2.96587 | 0.0100052 | 7.39543e-06 | 3.16947e-06 | 1(Win) | true |
| simdjson (ondemand) | 1264.35 | 0.114406 | 7842.38ms | 94653 | 40 | 266865 | 71394.6 | 0.0201036 | 4.07346 | 16.5912 | 3.09837 | 0.0118058 | 3.69772e-06 | 0 | 2(Loss) | true |
