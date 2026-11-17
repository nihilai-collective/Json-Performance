
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15520 | 0.141967 | 5865.58ms | 7351818 | 80 | 3.29057e+07 | 451754 | 0.168191 | 0.324837 | 1.62913 | 0.0669813 | 0.00111229 | 0.0211596 | 7.58384e-05 | 1(Win) | true |
| simdjson (stage-1) | 13979.1 | 0.0976008 | 6512.37ms | 7351818 | 160 | 3.83406e+07 | 501552 | 0.366949 | 0.3649 | 1.58986 | 0.0660409 | 0.000865102 | 0.0211797 | 8.59626e-05 | 2(Loss) | true |
