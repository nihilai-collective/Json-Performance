
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1407.88 | 0.0309074 | 1320.37ms | 8150 | 4890 | 14237.1 | 5520.69 | 0.0280842 | 3.6832 | 15.8741 | 3.13239 | 0.00546594 | 3.46017e-05 | 9.10836e-06 | 1(Win) | true |
| simdjson (ondemand) | 882.998 | 0.0459225 | 1647.06ms | 8150 | 1280 | 20915 | 8802.34 | 0.115025 | 5.85785 | 26.2214 | 5.13166 | 0.0126424 | 1.87883e-05 | 1.24617e-06 | 2(Loss) | true |
