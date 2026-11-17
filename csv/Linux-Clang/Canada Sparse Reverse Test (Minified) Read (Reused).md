
----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5984.36 | 0.0613858 | 8714.11ms | 2090234 | 30 | 1.25433e+06 | 333102 | 0.109666 | 0.844523 | 4.69125 | 0.718804 | 0.00260988 | 0.0762639 | 5.13499e-06 | 1(Win) | true |
| simdjson (ondemand) | 4905.19 | 0.833781 | 5286ms | 2090234 | 640 | 7.34787e+09 | 406386 | 0.37118 | 1.03949 | 5.09748 | 0.738318 | 0.00253841 | 0.0758111 | 1.1026e-06 | 2(Loss) | true |
