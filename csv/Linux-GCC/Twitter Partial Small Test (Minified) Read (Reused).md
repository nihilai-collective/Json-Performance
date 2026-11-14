
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6008.18 | 0.168591 | 767.684ms | 2889 | 160 | 95.6305 | 458.569 | 0.200754 | 0.945189 | 3.75666 | 0.480789 | 0.000346141 | 1.51436e-05 | 0 | 1(Win) | true |
| Jsonifier | 5876.43 | 0.228949 | 765.222ms | 2889 | 80 | 92.1797 | 468.85 | 0.101414 | 0.957087 | 3.75666 | 0.480789 | 0.000346141 | 3.46141e-05 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 5802.79 | 0.179554 | 767.915ms | 2889 | 160 | 116.287 | 474.8 | 0.0342367 | 0.963004 | 3.82451 | 0.399446 | 0.000400225 | 2.16338e-06 | 0 | 3(Loss) | true |
| simdjson (reflection) | 5738.96 | 0.153002 | 768.654ms | 2889 | 160 | 86.3267 | 480.081 | 0.0169214 | 0.972945 | 3.81239 | 0.406023 | 0.000361284 | 6.49013e-06 | 0 | 4(Loss) | true |
| Glaze | 3175.71 | 0.235132 | 806.05ms | 2889 | 40 | 166.456 | 867.575 | 0.125672 | 1.69578 | 7.17965 | 1.22603 | 0.000372101 | 0 | 0 | 5(Loss) | true |
