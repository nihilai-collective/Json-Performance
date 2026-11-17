
----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8959.15 | 0.271041 | 7343.63ms | 5212421 | 30 | 6.78482e+07 | 554847 | 0.00574967 | 0.565148 | 2.54442 | 0.309596 | 0.00224566 | 0.0590648 | 2.36614e-06 | 1(Win) | true |
| simdjson (ondemand) | 7771.52 | 0.238886 | 8271.59ms | 5212421 | 640 | 1.49427e+09 | 639637 | 0.172993 | 0.65241 | 2.85495 | 0.331074 | 0.00213405 | 0.0590408 | 4.85619e-06 | 2(Loss) | true |
