
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3304.86 | 0.126856 | 738.942ms | 905 | 320 | 35.1207 | 261.153 | 0.0107707 | 1.79465 | 7.77459 | 0.271823 | 0.00221685 | 1.38122e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 3189.6 | 0.17671 | 744.095ms | 905 | 320 | 73.1642 | 270.591 | 0.0796233 | 1.85633 | 8.44862 | 1.05083 | 0.00116022 | 0.000141575 | 6.90608e-06 | 2(Loss) | true |
| Glaze | 684.641 | 0.049074 | 846.456ms | 905 | 80 | 30.6171 | 1260.62 | 0.00991473 | 7.76464 | 22.0398 | 3.36685 | 0.00553867 | 5.52486e-05 | 0 | 3(Loss) | true |
