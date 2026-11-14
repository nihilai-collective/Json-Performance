
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1809.04 | 0.0220942 | 4704.54ms | 65103 | 4890 | 281173 | 34320.5 | 0.0237038 | 2.84123 | 10.182 | 1.90286 | 0.00864337 | 1.13616e-05 | 4.00184e-06 | 1(Win) | true |
| simdjson (ondemand) | 1441.45 | 0.0481165 | 5589.07ms | 65103 | 1280 | 549795 | 43072.6 | 0.105068 | 3.55684 | 13.8299 | 2.45393 | 0.0129471 | 2.07364e-05 | 7.68014e-06 | 2(Loss) | true |
