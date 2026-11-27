
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4416.39 | 0.154846 | 8187.46ms | 699405 | 640 | 3.50028e+07 | 151029 | 0.307845 | 1.14129 | 4.31603 | 0.737401 | 0.00440979 | 0.00290925 | 2.70319e-06 | 1(Win) | true |
| Glaze | 3852.32 | 0.161284 | 9152.06ms | 699405 | 160 | 1.24772e+07 | 173144 | 0.218105 | 1.29067 | 5.22079 | 1.16228 | 0.00244881 | 0.000895011 | 3.30638e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2294.7 | 0.161567 | 8315.18ms | 767297 | 640 | 1.69886e+08 | 318887 | 0.145076 | 2.16441 | 8.64826 | 1.18029 | 0.0032486 | 0.100863 | 1.16175e-05 | 3(Loss) | true |
