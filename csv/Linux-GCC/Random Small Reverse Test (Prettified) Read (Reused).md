
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1408.19 | 0.0244227 | 1308.08ms | 8150 | 4890 | 8885.62 | 5519.44 | 0.0307268 | 3.68205 | 15.8741 | 3.13239 | 0.00560749 | 3.67596e-05 | 3.53796e-06 | 1(Win) | true |
| simdjson (ondemand) | 902.819 | 0.0309582 | 1620.33ms | 8150 | 2560 | 18184.7 | 8609.08 | 0.0245819 | 5.72838 | 26.2048 | 5.12785 | 0.0105504 | 2.20475e-05 | 3.93021e-06 | 2(Loss) | true |
