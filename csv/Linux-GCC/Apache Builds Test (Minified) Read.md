
----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14567 | 0.0202337 | 1336.18ms | 94653 | 4890 | 7687.55 | 6196.76 | 0.0460742 | 0.35592 | 1.71452 | 0.0716301 | 3.14355e-05 | 1.73273e-06 | 2.83027e-07 | 1(Win) | true |
| simdjson (stage-1) | 13436.3 | 0.0314562 | 1388.4ms | 94653 | 1280 | 5716.5 | 6718.22 | 0.0391696 | 0.38547 | 2.00727 | 0.0771028 | 2.47367e-05 | 1.93965e-06 | 6.10784e-07 | 2(Loss) | true |
