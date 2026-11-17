
----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4013.79 | 0.0934021 | 835.09ms | 4857 | 1280 | 1487.14 | 1154.02 | 0.0314697 | 1.32716 | 5.54561 | 0.890057 | 0.000848485 | 2.28407e-05 | 1.12595e-06 | 1(Win) | true |
| simdjson (ondemand) | 3587.58 | 0.0908685 | 853.506ms | 4857 | 320 | 440.462 | 1291.12 | 0.115561 | 1.48152 | 6.03212 | 0.836319 | 0.000314623 | 3.34569e-05 | 1.2868e-05 | 2(Loss) | true |
