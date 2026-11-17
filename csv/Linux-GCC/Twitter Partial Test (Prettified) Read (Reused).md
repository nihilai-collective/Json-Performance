
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10125 | 0.212135 | 5953.91ms | 631514 | 2560 | 4.07606e+07 | 59482.3 | 0.104468 | 0.244399 | 1(Win) | true |
| Jsonifier (two-stage) | 10039.1 | 0.110322 | 6128.95ms | 631514 | 640 | 2.80342e+06 | 59991.6 | 0.0419923 | 0.246492 | 2(Loss) | true |
| simdjson (reflection) | 9100.38 | 0.0915773 | 6861.85ms | 631514 | 1280 | 4.70146e+06 | 66179.5 | 0.369964 | 0.271923 | 3(Loss) | true |
| simdjson (ondemand) | 8865.07 | 0.112598 | 6652.52ms | 631514 | 640 | 3.74495e+06 | 67936.1 | 0.0965717 | 0.279157 | 4(Loss) | true |
| Glaze | 3717.61 | 0.161437 | 7968.59ms | 631514 | 80 | 5.47187e+06 | 162002 | 1.04948 | 0.665857 | 5(Loss) | true |
