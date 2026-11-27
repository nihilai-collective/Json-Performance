
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1913.11 | 0.136292 | 4564.36ms | 65103 | 80 | 156515 | 32453.5 | 0.133136 | 2.69415 | 9.81215 | 1.80822 | 0.00820988 | 3.43686e-05 | 2.41924e-05 | 1(Win) | true |
| simdjson (ondemand) | 1486.44 | 0.25963 | 5503.89ms | 65103 | 30 | 352809 | 41769 | 0.00422943 | 3.46671 | 12.9965 | 2.46098 | 0.0144627 | 9.62577e-05 | 7.83374e-05 | 2(Loss) | true |
