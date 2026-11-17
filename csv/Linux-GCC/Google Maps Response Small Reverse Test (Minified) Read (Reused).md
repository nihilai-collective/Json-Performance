
----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 808.942 | 0.0778095 | 1257.14ms | 4390 | 4890 | 79299.2 | 5175.44 | 0.0925123 | 6.41956 | 28.0442 | 5.64761 | 0.0109828 | 0.000124004 | 6.8011e-05 | 1(Win) | true |
| simdjson (ondemand) | 739.621 | 0.155648 | 1307.67ms | 4390 | 160 | 12419.8 | 5660.51 | 0.0874818 | 7.00836 | 30.2786 | 5.86401 | 0.0112201 | 5.83713e-05 | 1.70843e-05 | 2(Loss) | true |
